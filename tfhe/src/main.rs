use bincode;

use std::fs::File;
use std::io::{Read, Write};
use std::ops::Add;

use tfhe::prelude::*;
use tfhe::{
    generate_keys, set_server_key, ClientKey, ConfigBuilder, FheUint3, FheUint4, ServerKey,
};

type FheUint = FheUint3;

/// Returns the value of:
///
/// cond_val1 * (1 + val2, val1, val0)
fn eval_then_branch(cond: &FheUint, then_branch: &[FheUint]) -> Vec<FheUint> {
    then_branch.iter().map(|value| value * cond).collect()
}

/// Returns the value of:
///
/// not cond_val1 * (2 + val2, val1, val0)
fn eval_else_branch(cond: &FheUint, else_branch: &[FheUint]) -> Vec<FheUint> {
    else_branch
        .iter()
        .map(|value| value * cond.map(not))
        .collect()
}

trait Cipher {
    type Output;

    fn mul_distr(&self, other: &[FheUint]) -> Self::Output;
}

impl Cipher for FheUint {
    type Output = Vec<FheUint>;

    fn mul_distr(&self, other: &[FheUint]) -> Self::Output {
        other.mul_distr(self)
    }
}

trait PackedCipher {
    type Output;

    fn add(self, other: Self) -> Self::Output;

    fn mul(self, other: Self) -> Self::Output;

    fn mul_distr(self, other: &FheUint) -> Self::Output;
}

impl PackedCipher for Vec<FheUint> {
    type Output = Vec<FheUint>;

    fn add(self, other: Self) -> Self::Output {
        self.iter().zip(other.iter()).map(|(a, b)| a + b).collect()
    }

    fn mul(self, other: Self) -> Self::Output {
        self.iter().zip(other.iter()).map(|(a, b)| a * b).collect()
    }

    fn mul_distr(self, other: &FheUint) -> Self::Output {
        self.iter().map(|value| value * other).collect()
    }
}

impl PackedCipher for &[FheUint] {
    type Output = Vec<FheUint>;

    fn add(self, other: Self) -> Self::Output {
        self.into_iter()
            .zip(other.into_iter())
            .map(|(a, b)| a + b)
            .collect()
    }

    fn mul(self, other: Self) -> Self::Output {
        self.iter()
            .zip(other.iter())
            .map(|(a, b)| a * b)
            .collect::<Vec<FheUint>>()
    }

    fn mul_distr(self, other: &FheUint) -> Self::Output {
        self.iter().map(|value| value * other).collect()
    }
}

fn not(val: u64) -> u64 {
    if val == 0 {
        1
    } else {
        0
    }
}

fn main() {
    let config = ConfigBuilder::all_disabled().enable_default_uint3().build();

    let client_key: ClientKey;
    let server_key: ServerKey;

    // Check if keys were generated (if files exist)
    if File::open("client.key").is_ok() && File::open("server.key").is_ok() {
        println!("Loading keys...");
        // Load keys from files
        client_key = bincode::deserialize(&std::fs::read("client.key").unwrap()).unwrap();
        server_key = bincode::deserialize(&std::fs::read("server.key").unwrap()).unwrap();
    } else {
        println!("Generating keys...");

        (client_key, server_key) = generate_keys(config);

        // Save keys to files
        File::create("client.key")
            .unwrap()
            .write_all(bincode::serialize(&client_key).unwrap().as_slice())
            .unwrap();

        File::create("server.key")
            .unwrap()
            .write_all(bincode::serialize(&server_key).unwrap().as_slice())
            .unwrap();
    }
    println!("Done.");

    set_server_key(server_key);

    let (val2, val1, val0): (FheUint, FheUint, FheUint) = [1, 3, 3]
        .map(|value| FheUint::encrypt(value, &client_key))
        .into();

    let cond_val0 = val0.ge(3);
    let cond_val1 = val1.ge(2);

    // if a > 3 && b > 2 {
    //     val2 = 1 + val2;
    // } else {
    //     val2 = 2 + val2;
    // }
    // time this

    let time = std::time::Instant::now();

    let all_packets_from_flattened_if = cond_val0
        .mul_distr(
            &cond_val1
                .mul_distr(&[1 + val2.clone(), val1.clone(), val0.clone()])
                .add(
                    cond_val1
                        .map(not)
                        .mul_distr(&[2 + val2.clone(), val1.clone(), val0.clone()]),
                ),
        )
        .add(
            cond_val0
                .map(not)
                .mul_distr(&[2 + val2.clone(), val1.clone(), val0.clone()]),
        );

    let all_packet_flattened_if_time = std::time::Instant::now() - time;

    let time = std::time::Instant::now();

    let val2_pbs =
        &cond_val0.bivariate_function(&cond_val1, |a, b| if 5 < a && 2 < b { 1 } else { 2 });

    let only_changed_values_pbs_time = std::time::Instant::now() - time;

    let time = std::time::Instant::now();

    let val2_from_flattened = &cond_val0
        * (&cond_val1 * (1 + &val2) + &cond_val1.map(not) * (2 + &val2))
        + &cond_val0.map(not) * (2 + &val2);

    let only_changed_values_flattened_if_time = std::time::Instant::now() - time;

    println!("Result:");
    println!("{}", val2_pbs.decrypt(&client_key));

    println!("Result from flattened:");
    println!("{}", val2_from_flattened.decrypt(&client_key));

    println!("Result:");
    all_packets_from_flattened_if
        .iter()
        .map(|value| value.decrypt(&client_key))
        .for_each(|value| println!("{}", value));

    println!(
        "Time taken for all packet flattened if: {:?}",
        all_packet_flattened_if_time.as_secs_f64()
    );
    println!(
        "Time taken for only changed values pbs: {:?}",
        only_changed_values_pbs_time.as_secs_f64()
    );
    println!(
        "Time taken for only changed values flattened if: {:?}",
        only_changed_values_flattened_if_time.as_secs_f64()
    );
}
