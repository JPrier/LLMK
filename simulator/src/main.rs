use simulator::*;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    if args.len() < 2 {
        print_usage();
        return;
    }
    
    match args[1].as_str() {
        "run" => {
            let default_scenario = "example".to_string();
            let scenario_name = args.get(2).unwrap_or(&default_scenario);
            run_simulator_with_scenario(scenario_name);
        },
        "benchmark" => {
            let scenario_filter = args.get(2);
            run_benchmarks_cmd(scenario_filter);
        },
        "test" => {
            run_integration_tests_cmd();
        },
        "list-scenarios" => {
            list_scenarios_cmd();
        },
        "memory" => {
            benchmark::benchmark_memory_usage();
        },
        "legacy" => {
            run_legacy_simulator();
        },
        _ => {
            println!("Unknown command: {}", args[1]);
            print_usage();
        }
    }
}