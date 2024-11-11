# Simple C++ HTTP Server

A lightweight HTTP server implemented in C++ that serves static files. This project demonstrates basic socket programming and HTTP request handling in C++.

## Features

- Static file serving (HTML, CSS, JS, images)
- Basic routing system
- MIME type detection
- Custom 404 error page
- Responsive web design
- Cross-platform compatibility

## Prerequisites

- C++17 or higher
- GCC/G++ compiler
- Make build system
- POSIX-compliant operating system (Linux, macOS, etc.)

## Project Structure

```
project/
├── src/
│   └── main.cpp
├── public/
│   ├── index.html
│   ├── about.html
│   ├── contact.html
│   ├── 404.html
│   └── styles.css
├── build/
├── bin/
├── Makefile
├── .gitignore
└── README.md
```

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/LucaPalminteri/http-cpp-server.git
   cd http-cpp-server
   ```

2. Install dependencies (Ubuntu/Debian):
   ```bash
   make install-deps
   ```

3. Build the project:
   ```bash
   make
   ```

## Usage

1. Start the server:
   ```bash
   make run
   ```

2. Open your web browser and navigate to:
   ```
   http://localhost:8080
   ```

The server will start listening on port 8080 and serve files from the `public` directory.

## Available Routes

- `/` - Home page
- `/about` - About page
- `/contact` - Contact page
- Any other path will serve files from the public directory or return a 404 error

## Development

### Adding New Routes

To add a new route, create an HTML file in the `public` directory and update the routing logic in `src/main.cpp` if needed.

### Styling

The project uses a single CSS file (`public/styles.css`) for styling all pages. Modify this file to change the appearance of the website.

### Building

- `make` - Build the project
- `make clean` - Remove build files
- `make run` - Build and run the server

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- POSIX socket programming documentation
- Modern C++ features and best practices
- Web development principles and responsive design

## Troubleshooting

### Common Issues

1. **Port already in use**
   ```bash
   Error: Bind failed
   ```
   Solution: Change the port number in `src/main.cpp` or kill the process using the current port.

2. **Permission denied**
   ```bash
   Error: Permission denied
   ```
   Solution: Make sure you have write permissions in the project directory.

3. **Styles not loading**
   - Check if the CSS file is being served correctly
   - Verify the file paths in HTML files
   - Check the browser's developer tools for network errors

### Debug Tools

1. Use browser developer tools (F12)
2. Check server console output
3. Monitor network requests

For more issues, please check the GitHub Issues page or create a new issue.
