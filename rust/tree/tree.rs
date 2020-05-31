struct Node {
    child: Option<NonZeroU32>,
    neighbour: Option<NonZeroU32>,
    parent: u32,
    value: u32,
}

// https://www.youtube.com/watch?v=sWgDk-o-6ZE
