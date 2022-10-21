
<h1 align="center">
	🪄 pipex
</h1>

### 🗝️ Original in [**Russian**](https://github.com/AYglazk0v/pipex/blob/master/README.md)

## 💡 About the project:

> This project aims to deepen your understanding of two concepts you already know: Redirections and Pipes. It is an introductory project for larger UNIX projects that will appear later in the course.

      This project consists of reproducing the behavior of a shell pipe by redirecting STDIN
	  and STDOUT using pipe().
	  Pipex is an individual project in 42 which requires us to create a program,
	  that mimics the behavior of a shell pipe, taking a file or reading from STDIN and
	  redirect to a sequence of commands that will be written to the output file.
	  To create the program we need to create child processes with fork(),
	  interacting with the parent process through pipe(), manipulating 
	  environment variable, checking if a command exists or if it has
	  permission to execute, e.g. printing errors in STDERR when needed,
	  returning the correct status code.

More information about the project can be found at  [**subject**](https://github.com/MKKurbandibirov/pipex/blob/master/Subject.pdf).

## 🛠 Testing и Usage:

	# Clone the project and access the folder
	git clone git@github.com:AYglazk0v/pipex.git && cd pipex/
	# Run make so that you can build the program with the obligatory part
	make
	# Create a file for use in the program input
	echo "aaaaaaaaaaaaaaaaaaaaaaaaaa" > input_file
	# Run the program as shown in the example
	./pipex "input_file" "tr a b" "tr b c" "output_file"
	# Check the output file
	cat output_file
	# or
	# Run make bonus to assemble the program with the bonus part
	make bonus
	# Run the program as shown in the example
	./pipex "here_doc" "END" "tr a b" "tr b c" "tr c d" "output_file"
	# Check the output file
	cat output_file
	# Clean up the output files with
	make fclean

To check how it works, you can compare the behavior of the program you wrote with that of any shell, in this example -- shell:
	

	 1. pipex ./pipex "input_file" "tr a b" "tr b c" "output_file"
		shell < input_file tr a b | tr b c > output_file
	 2.	pipex ./pipex "input_file" "ls -l" "wc -l" "output_file"
		shell < input_file ls -l | wc -l > output_file
	 3.	pipex ./pipex "here_doc" "END" "rev" "sort -r" "tr '\n' ' ' '" "output_file"
		shell << END rev | sort -r | tr '\n' ' ' ' >> output_file
