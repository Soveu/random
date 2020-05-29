RUST=rustc -C opt-level=3 -C target-cpu=native
CXX=clang++ -O3 -march=native -std=c++20
PERF=perf stat -d

all:
	$(RUST) binsearch.rs
	$(RUST) btree.rs
	$(RUST) hash.rs
	$(CXX)  set.cpp -o set
	$(CXX)  unordered_set.cpp -o unordered_set

perf:
	$(PERF) ./binsearch	< /dev/shm/input.txt &>  results.txt 
	$(PERF) ./btree		< /dev/shm/input.txt &>> results.txt
	$(PERF) ./hash		< /dev/shm/input.txt &>> results.txt
	$(PERF) ./set 		< /dev/shm/input.txt &>> results.txt
	$(PERF) ./unordered_set	< /dev/shm/input.txt &>> results.txt

