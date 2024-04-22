use bincode;

use std::fs::File;
use std::io::{Write};

use tfhe::prelude::*;
use tfhe::{
    generate_keys, set_server_key, ClientKey, ConfigBuilder, FheUint4, ServerKey,
};

use config_file::FromConfigFile;
use serde::Deserialize;
use lazy_static::lazy_static;

#[derive(Deserialize)]
pub struct Config {
    pub values: Vec<i32>,
}

lazy_static!{
    pub static ref CONFIG: Config = Config::from_config_file("config.toml").unwrap();
}


type FheUint = FheUint4;

fn main() {
	let config = ConfigBuilder::all_disabled().enable_default_uint4().build();

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

	// Split the input by whitespaces and collect them into a vector of strings
	let values: &Vec<i32> = &CONFIG.values;

	set_server_key(server_key);
	// Packet Borrow Next Secret
	let val0: FheUint = FheUint::encrypt(values[0], &client_key);
	let val1: FheUint = FheUint::encrypt(values[1], &client_key);
	let val2: FheUint = FheUint::encrypt(values[2], &client_key);
	let val3: FheUint = FheUint::encrypt(values[3], &client_key);
	let val4: FheUint = FheUint::encrypt(values[4], &client_key);
	let val5: FheUint = FheUint::encrypt(values[5], &client_key);
	let val6: FheUint = FheUint::encrypt(values[6], &client_key);
	let val7: FheUint = FheUint::encrypt(values[7], &client_key);
	let val8: FheUint = FheUint::encrypt(values[8], &client_key);
	let val9: FheUint = FheUint::encrypt(values[9], &client_key);
	let val10: FheUint = FheUint::encrypt(values[10], &client_key);
	let time = std::time::Instant::now();
	let c1 = val0.bivariate_function(&val5, |val0, val5| if 0 != val0 && val5 >= 4 { 1 } else { 0 });
	let c0 = val0.bivariate_function(&val5, |val0, val5| if 0 != val0 && !(val5 >= 4) { 1 } else { 0 });
	let c3 = val0.bivariate_function(&val5, |val0, val5| if !(0 != val0) && val5 >= 4 { 1 } else { 0 });
	let c8 = val0.bivariate_function(&val5, |val0, val5| if !(0 != val0) && !(val5 >= 4) { 1 } else { 0 });
	// let c2 = val6.bivariate_function(&val7, |val6, val7| if 6 + val6 <= val7 { 1 } else { 0 });
	let c2_0 = val6.bivariate_function(&val7, |val6, val7| if 6 + val6 <= val7 { 0 } else { 1 });
	let c5 = val8.bivariate_function(&val9, |val8, val9| if val8 >= 6 && 3 < val9 { 1 } else { 0 });
	let c4 = val8.bivariate_function(&val9, |val8, val9| if val8 >= 6 && !(3 < val9) { 1 } else { 0 });
	let c7 = val8.bivariate_function(&val9, |val8, val9| if !(val8 >= 6) && 3 < val9 { 1 } else { 0 });
	let c6 = val8.bivariate_function(&val9, |val8, val9| if !(val8 >= 6) && !(3 < val9) { 1 } else { 0 });
	// let c14 = val8.map(|val8| if val8 >= 6 { 1 } else { 0 });
	let c14_0 = val8.map(|val8| if val8 >= 6 { 0 } else { 1 });

    let val10 = (1 + &c2_0) * &c4 * &c0 +
		(&c5 + &c6) * ((&c0 + &c1) * (&c2_0 + 1) + &c0) +
		(&c14_0 + &c2_0) * &c3 +
		(3 + &c2_0) * &c7 * &c0 +
		(2 * &c7 + &c4 * &c2_0) * &c1 +
		(1 + &c2_0 + &c14_0) * &c8;
	// let val10_0 = 1 * &c6_1 * &c2_1 * &c0_1;
	// let val10_1 = 0 * &c6_0 * &c2_1 * &c0_1;
	// let val10_2 = 2 * &c7_1 * &c2_1 * &c0_1;
	// let val10_3 = 1 * &c7_0 * &c2_1 * &c0_1;
	// let val10_4 = 2 * &c6_1 * &c2_0 * &c0_1;
	// let val10_5 = 1 * &c6_0 * &c2_0 * &c0_1;
	// let val10_6 = 3 * &c7_1 * &c2_0 * &c0_1;
	// let val10_7 = 2 * &c7_0 * &c2_0 * &c0_1;
	// let val10_8 = 2 * &c6_1 * &c2_1 * &c0_0;
	// let val10_9 = 1 * &c6_0 * &c2_1 * &c0_0;
	// let val10_10 = 3 * &c7_1 * &c2_1 * &c0_0;
	// let val10_11 = 2 * &c7_0 * &c2_1 * &c0_0;
	// let val10_12 = 3 * &c6_1 * &c2_0 * &c0_0;
	// let val10_13 = 2 * &c6_0 * &c2_0 * &c0_0;
	// let val10_14 = 4 * &c7_1 * &c2_0 * &c0_0;
	// let val10_15 = 3 * &c7_0 * &c2_0 * &c0_0;
	// let val10_16 = 0 * &c14_1 * &c2_1 * &c1_1;
	// let val10_17 = 1 * &c14_0 * &c2_1 * &c1_1;
	// let val10_18 = 1 * &c14_1 * &c2_0 * &c1_1;
	// let val10_19 = 2 * &c14_0 * &c2_0 * &c1_1;
	// let val10_20 = 1 * &c14_1 * &c2_1 * &c1_0;
	// let val10_21 = 2 * &c14_0 * &c2_1 * &c1_0;
	// let val10_22 = 2 * &c14_1 * &c2_0 * &c1_0;
	// let val10_23 = 3 * &c14_0 * &c2_0 * &c1_0;
	// let val10 = val10_0 + val10_1 + val10_2 + val10_3 + val10_4 + val10_5 + val10_6 + val10_7 + val10_8 + val10_9 + val10_10 + val10_11 + val10_12 + val10_13 + val10_14 + val10_15 + val10_16 + val10_17 + val10_18 + val10_19 + val10_20 + val10_21 + val10_22 + val10_23;
	let elapsed_time = std::time::Instant::now() - time;
	println!("Result:");
	println!("val0: {}", val0.decrypt(&client_key));
	println!("val1: {}", val1.decrypt(&client_key));
	println!("val2: {}", val2.decrypt(&client_key));
	println!("val3: {}", val3.decrypt(&client_key));
	println!("val4: {}", val4.decrypt(&client_key));
	println!("val5: {}", val5.decrypt(&client_key));
	println!("val6: {}", val6.decrypt(&client_key));
	println!("val7: {}", val7.decrypt(&client_key));
	println!("val8: {}", val8.decrypt(&client_key));
	println!("val9: {}", val9.decrypt(&client_key));
	println!("val10: {}", val10.decrypt(&client_key));

	println!("Time taken: {:?}", elapsed_time.as_secs_f64());
}
