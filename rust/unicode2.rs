type ℂ = f64;

fn Σ(i: impl Iterator<Item = ℂ>) -> ℂ {
    i.sum()
}

fn ζ(𝓈: ℂ) -> ℂ {
    Σ((1.0 .. ℂ::INFINITY).map(|n| n.powf(-𝓈)))
}

fn main() {
    let x = ζ(42.0);
}
