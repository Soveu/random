#![feature(const_generics)]

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum Op {
    Sell,
    Buy,
}

pub fn cost<const OP: Op>(price: i32, delta: i32) -> i32 {
    match OP {
        Op::Sell => price + delta,
        Op::Buy  => price - delta,
    }
}

pub fn buy(money: i32) -> i32 {
    money - cost::<Op::Buy>(60, 20)
}

pub fn sell(money: i32) -> i32 {
    money + cost::<Op::Sell>(75, 25)
}

fn main() {
    let mut money = 100;
    money = buy(money);
    money = sell(money);
    println!("{}", money);
}

