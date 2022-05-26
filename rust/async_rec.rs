use std::pin::Pin;
use std::path::PathBuf;

pub async fn create_dep_symlinks(mut dep_dir: PathBuf, dependencies: Vec<String>) {
    if dependencies.len() != 0 {
        let user_profile = std::env::var("USERPROFILE").unwrap();
        let mut volt_dir: PathBuf = user_profile.into();
        volt_dir.push(".volt");

        for dep in dependencies {
            /* This is a bit more portable and probably safer version of this
             * let dep_dir = format!(r"{}\node_modules\{}", current_dep_dir, dep); */
            dep_dir.push("node_modules");
            dep_dir.push(&dep);

            let response: Package = get_yarn_response(dep).await;

            let deps = response.versions[&response.dist_tags.latest].dependencies;
            let deps: Vec<String> = deps.into_iter()
                .map(|(key, _value)| key)
                .collect();

            let boxed_self: Pin<Box<_>> = Box::pin(create_dep_symlinks(dep_dir, deps));
            boxed_self.await;
        }
    }
}

fn main() {}
