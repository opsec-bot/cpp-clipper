# Crypto Clipper

Crypto Clipper is a C++ program that monitors the Windows clipboard for cryptocurrency addresses and replaces them with new addresses of the same type. This is a security measure that can help prevent cryptocurrency theft by replacing copied addresses with new ones that belong to the user.

## Prerequisites

Crypto Clipper requires a Windows operating system to run. The following software is also required:

- A C++ compiler
- Windows.h library

## Installation

1. Clone or download the Crypto Clipper repository.
2. Compile the program with your C++ compiler.
3. Run the compiled program.

## Usage

Simply run the compiled program to begin monitoring the Windows clipboard for cryptocurrency addresses. When an address is detected, it will be replaced with a new address of the same type.

## Supported Cryptocurrencies

- Monero
- Litecoin
- Bitcoin
- Ethereum
- Stellar
- XRP
- Bitcoin Cash
- Dogecoin
- Dash
- NEO


https://user-images.githubusercontent.com/71150660/230821824-56d33b1e-3c74-4c1b-8060-253d93937484.mp4



## Configuration

The addresses that Crypto Clipper monitors for can be configured in the `addresses` map in the source code. Each supported cryptocurrency has an entry in the map that specifies the regex pattern to match addresses of that type, the message to print when an address is detected, and the new address to replace it with.

## Contributing

Crypto Clipper is an open-source project and contributions are welcome! To contribute, simply fork the repository, make your changes, and submit a pull request.

## License

Crypto Clipper is released under the [MIT License](https://opensource.org/licenses/MIT).
