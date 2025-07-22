fn main() {
    println!(
        "cargo:rustc-link-search={}",
        std::env::var("CARGO_MANIFEST_DIR").unwrap()
    );
    println!("cargo:rustc-link-arg=-Tmemory.x");
    println!("cargo:rerun-if-changed=memory.x");
}
