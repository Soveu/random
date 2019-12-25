
struct Node {
    neighbours: Vec::<usize>,
    name:       String,
}

type Graph = Vec::<Node>;

fn topological_sort(g: &Graph) -> Vec::<usize> {
    let mut res = Vec::with_capacity(g.len());
    let mut stack = Vec::with_capacity(g.len());
    let mut visited = Vec::with_capacity(g.len());
    visited.resize(g.len(), false);

    for i in 0..g.len() {
        if visited[i] {
            continue;
        }

        stack.push((i, false));
        loop {
            let (n, working) = match stack.pop() {
                Some(x) => x,
                None => break,
            };
            visited[n] = true;

            if working {
                res.push(n);
            } else {
                stack.push((n, true));
            }

            for neighbour in &g[n].neighbours {
                if !visited[*neighbour] {
                    stack.push((*neighbour, false));
                }
            }
        }
    }

    return res;
}

fn main() {
    let g: Graph = vec![
        Node{neighbours: vec![1], name: "socks".to_string()},
        Node{neighbours: vec![], name: "underwear".to_string()},
        Node{neighbours: vec![0, 1], name: "pants".to_string()},
        Node{neighbours: vec![1], name: "tshirt".to_string()},
        Node{neighbours: vec![3], name: "jacket".to_string()},
        Node{neighbours: vec![0, 2], name: "boots".to_string()},
    ];

    let r = topological_sort(&g);
    for i in r {
        println!("{}", g[i].name);
    }
}

