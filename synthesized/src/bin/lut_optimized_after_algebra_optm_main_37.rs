use bincode;

use std::fs::File;
use std::io::{Read, Write};

use tfhe::prelude::*;
use tfhe::{generate_keys, set_server_key, ClientKey, ConfigBuilder, FheUint4, ServerKey};

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
	// let val10: FheUint = FheUint::encrypt(values[10], &client_key);
	let time = std::time::Instant::now();
	let c0 = val6.bivariate_function(&val7, |val6, val7| if 6 + val6 <= val7 { 1 } else { 0 });
	let c0_0 = val6.bivariate_function(&val7, |val6, val7| if 6 + val6 <= val7 { 0 } else { 1 });
	let c1 = val5.map(|val5| if val5 >= 4 { 1 } else { 0 });
	let c1_0 = val5.map(|val5| if val5 >= 4 { 0 } else { 1 });
	let c2 = val8.bivariate_function(&val0, |val8, val0| if val8 >= 6 && 0 != val0 { 1 } else { 0 });
	let c3 = val8.bivariate_function(&val0, |val8, val0| if val8 >= 6 && !(0 != val0) { 1 } else { 0 });
	let c4 = val8.bivariate_function(&val0, |val8, val0| if !(val8 >= 6) && 0 != val0 { 1 } else { 0 });
	let c5 = val8.bivariate_function(&val0, |val8, val0| if !(val8 >= 6) && !(0 != val0) { 1 } else { 0 });
	// let c6 = val8.map(|val8| if val8 >= 6 { 1 } else { 0 });
	let c6_0 = val8.map(|val8| if val8 >= 6 { 0 } else { 1 });
	let c7 = val9.map(|val9| if 3 < val9 { 1 } else { 0 });
	// let c7_0 = val9.map(|val9| if 3 < val9 { 0 } else { 1 });
	let c8 = val0.map(|val0| if 0 != val0 { 1 } else { 0 });
	// let c8_0 = val0.map(|val0| if 0 != val0 { 0 } else { 1 });

	// zero
	let res_1st_part = (&c0 << 3) | (&c1 << 2) | (&c0_0 << 1) | &c5;
	let res_2nd_part = (&c3 << 3) | (&c7 << 2) | (&c2 << 1) | &c4;

	// c0, c1, c0_0, c5 | c3, c7, c2, c4
	let res_1st_part = res_1st_part.bivariate_function(&res_2nd_part, |part1, part2| {
		let c0 = (part1 >> 3) & 1;
		let c1 = (part1 >> 2) & 1;
		let c0_0 = (part1 >> 1) & 1;
		let c5 = part1 & 1;
		let c3 = (part2 >> 3) & 1;
		let c7 = (part2 >> 2) & 1;
		let c2 = (part2 >> 1) & 1;
		let c4 = part2 & 1;

		return (c0 + c1 * c0_0 + c1 ^ c0) * c5 +
			(c1 ^ c0) * c3 +
			(c7 * (c0 + c1 * c0_0) + c1 ^ c0) * c2 +
			((c7 + 1) * (c0 + c1 * c0_0) + c1 ^ c0) * c4;
	});

	let res_2nd_part = (&c6_0 << 3) | (&c7 << 2) | (&c8 << 1) | &c1_0;
	let temp_part = c0_0;

	// c6_0, c7, c8, c1_0 | c0_0
	let res_2nd_part = res_2nd_part.bivariate_function(&temp_part, |part1, part2| {
		let c6_0 = (part1 >> 3) & 1;
		let c7 = (part1 >> 2) & 1;
		let c8 = (part1 >> 1) & 1;
		let c1_0 = part1 & 1;
		let c0_0 = part2 & 1;

		return (2 + c6_0 + c7 * c8) * c1_0 * c0_0;
	});

	// c0, c1, c0_0, c5 | c3, c7, c2, c4   -   c6_0, c7, c8, c1_0 | c0_0
	let val10 = res_1st_part + res_2nd_part;
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
