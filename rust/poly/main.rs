struct Game {
    enemies:    Vec<Enemy>,
    playername: String,
}

struct Enemy {
    health:     i32,
    behavior:   fn(&mut Game, usize),
    on_death:   fn(&mut Game, usize),
}

fn do_nothing(_: &mut Game, _: usize) {
    return;
}

fn farewell(g: &mut Game, _: usize) {
    println!("Farewell, {}!", g.playername);
}

fn main() {
    let mut g = Game{
        enemies: vec![Enemy{health: 0, behavior: do_nothing, on_death: farewell}],
        playername: "Soveu".to_string(),
    };

    (g.enemies[0].on_death)(&mut g, 0);
}

