use std::collections::{HashMap, HashSet};

#[derive(Clone, Debug, Default)]
struct Node {
    neighbours: Vec::<usize>,
    id:         char,
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

fn reverse(g: &Graph) -> Graph {
    let mut res = Graph::new();
    res.resize(g.len(), Default::default());

    for (i, node) in g.iter().enumerate() {
        res[i].id = g[i].id;
        for n in node.neighbours.iter() {
            res[*n].neighbours.push(i);
        }
    }

    return res;
}

#[derive(Clone, Debug, Default)]
struct StronglyConnectedNode {
    nodes:  Vec::<usize>,
    edges:  HashSet::<usize>,
}

type StronglyConnectedGraph = Vec::<StronglyConnectedNode>;

fn connect_into_strongly_connected_graph(mut scg: StronglyConnectedGraph, g: &Graph) -> StronglyConnectedGraph {
    let mut map = HashMap::new();

    for (i, group) in scg.iter().enumerate() {
        for node in &group.nodes {
            map.insert(*node, i);
        }
    }

    for (i, group) in scg.iter_mut().enumerate() {
        for node in &group.nodes {
            for neighbour in &g[*node].neighbours {
                let n = map[&*neighbour];
                if n != i {
                    group.edges.insert(n);
                }
            }
        }
    }
    
    return scg;
}

fn strongly_connected(g: &Graph) -> (Graph, Vec::<usize>, StronglyConnectedGraph) {
    let rev = reverse(g);
    let topo = topological_sort(g);

    let mut res = Vec::new();
    let mut stack = Vec::new();
    let mut visited = Vec::new();
    visited.resize(g.len(), false);

    for n in topo.iter().rev() {
        if visited[*n] {
            continue;
        }

        let mut stronglyConnected = Vec::new();
        stack.push((*n, false));

        loop {
            let (node, working) = match stack.pop() {
                Some(x) => x,
                None => break,
            };
            visited[node] = true;

            if working {
                stronglyConnected.push(node);
            } else {
                stack.push((node, true));
            }

            for neighbour in &rev[node].neighbours {
                if !visited[*neighbour] {
                    stack.push((*neighbour, false));
                }
            }
        }

        res.push(StronglyConnectedNode{
            nodes: stronglyConnected,
            edges: Default::default(),
        });
    }

    res = connect_into_strongly_connected_graph(res, &g);
    return (rev, topo, res);
}

fn main() {
    let g = vec![
        Node{id: 'A', neighbours: vec![1]},
        Node{id: 'B', neighbours: vec![2, 3]},
        Node{id: 'C', neighbours: vec![0]},
        Node{id: 'D', neighbours: vec![4]},
        Node{id: 'E', neighbours: vec![5]},

        Node{id: 'F', neighbours: vec![3]},
        Node{id: 'G', neighbours: vec![5, 7]},
        Node{id: 'H', neighbours: vec![8]},
        Node{id: 'I', neighbours: vec![9]},
        Node{id: 'J', neighbours: vec![6, 10]},

        Node{id: 'K', neighbours: vec![]},
    ];

    let (rev, topo, res) = strongly_connected(&g);
    println!("{:?}", g);
    println!("{:?}", rev);
    println!("{:?}", topo);
    println!("{:?}", res);
}

