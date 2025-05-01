#include <iostream>

long ptrace(enum __ptrace_request request, pid_t pid, void *addr, void *data);

class debugger {
public:
	debugger (std::string prog_name, pid_t pid)
		: m_prog_name{std::move(prog_name)}, m_pid{pid} {}

	void run();

private:
	std::string m_prog_name;
	pid_t m_pid;


};

int main(int argc, char* argv[]){
	if (argc < 2){
		std::cerr << "Program name not specified";
		return -1;
	}

	auto prog = argv[1];

	auto pid = fork();

	if (pid == 0){
		//we're in the child process
		//execute debugee
		ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
		execl(prog, prog, nullptr);
	}
	else if (pid >= 1){
		//we're in the parent process
		//execute debugger
		std::count << "Start debugging process " << pid << "\n";
		debugger dbg{prog, pid};
		dbg.run();
	}
}
