mod database;

extern crate rocket;
use std::time::Instant;


//use rocket::{
//    serde::{json::Json, Deserialize, Serialize},
//};
//
//#[derive(Deserialize, Serialize)]
//struct WordsResponse {
//    words: String,
//}

//#[rocket::get("/words", format = "json")]
//fn get_words() -> Json<WordsResponse> {
//    let words: String = String::from("Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. \
//                                         Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. \
//                                         Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. \
//                                         Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. ");
//    Json( WordsResponse { words } )
//}

fn main() {
    println!("test");

//    let bytes = include_bytes!("../words/russian.txt");
//    let string_data = String::from_utf8_lossy(bytes);
//    let words: Vec<&str> = string_data.split('\n').collect();

    let mut client = database::init_connection("127.0.0.1", "test_db", "test_user", "12345678").unwrap();
    let before = Instant::now();
//    let _first_words = database::get_words(&mut client).unwrap();
    let _first_words = database::get_n_words(&mut client, 1000).unwrap();
    println!("Request elapsed time: {:.2?}", before.elapsed());
    // if let Err(err) = rocket::build()
    //     .mount("/", rocket::routes![get_words])
    //     .launch()
    //     .await
    // {
    //     println!("Rocket Rust couldn't take off successfully!");
    //     drop(err); // Drop initiates Rocket-formatted panic
    // }
}

