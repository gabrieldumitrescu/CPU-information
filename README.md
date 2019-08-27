# CPU-information

An application to print information about the installed CPU using the CPUID assembly instruction.
It compiles and runs on Linux x86-64 arch.

## Getting Started
Needs NASM assembler and a C compiler (gcc). 
### Prerequisites
NASM assembler can be installed on most distributions using the corresponding package manager.
On Ubuntu:
```
sudo apt install nasm
```
Gcc compiler can also be easily installed with:
```
sudo apt install gcc
```
Though I recommend installing the ```build-essential``` instead to get other utilities like ```g++``` and ```make```. 

### Compilation
Compile by running:
```
make
```
## Running
Run the CPU-info program to see the gathered information.

## Author

* **Gabriel Dumitrescu** - *Initial work* -

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgements

*  I used this page on wikipedia https://en.wikipedia.org/wiki/CPUID and cpuid assembly instruction documentation.



