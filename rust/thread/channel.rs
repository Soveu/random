use std::thread;
use std::sync::mpsc;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel();

    let tx1 = tx.clone();
    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];

        for val in vals {
            tx1.send(val).unwrap();
        }
        println!("Thread1 done");
    });

    thread::spawn(move || {
        let vals = vec![
            String::from("moar"),
            String::from("messages"),
            String::from("from"),
            String::from("thread2"),
        ];

        for val in vals {
            tx.send(val).unwrap();
        }
        println!("Thread2 done");
    });


    for received in rx {
        println!("Got: {}", received);
        thread::sleep(Duration::from_secs(1));
    }
}

