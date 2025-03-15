# REST API with C++ and Drogon

This repository contains the implementation of a REST API using the Drogon framework in C++.

## Technologies Used
- **C++**
- **Drogon** (web framework in C++)
- **XMake** (for build management)
- **sqlite_orm** (orm)

## Requirements
Before starting, ensure you have installed:
- **C++17 or later**
- **XMake**
- **Drogon** 

## Installation and Setup
1. Clone the repository:
   ```sh
   git clone https://github.com/eloidenovela/restapi-with-drogon.git
   cd restapi-with-drogon
   ```
2. Build the project using XMake:
   ```sh
   xmake
   ```
3. Configure the database (if necessary) and adjust the `config.json` file.
4. Run the application:
   ```sh
   xmake run restapi-drogon
   ```

## Available Endpoints
The API exposes the following endpoints:

### **GET /**
- **Description:** Default endpoint for status check.
- **Response:**
  ```json
  {
    "message": "API online"
  }
  ```

### **GET /users**
- **Description:** Returns a list of registered users.
- **Response:**
  ```json
  [
    {
      "id": 1,
      "name": "John Doe",
      "email": "john@email.com"
    }
  ]
  ```

### **POST /users**
- **Description:** Registers a new user.
- **Request:**
  ```json
  {
    "name": "Maria Smith",
    "email": "maria@email.com"
  }
  ```
- **Response:**
  ```json
  {
    "id": 2,
    "name": "Maria Smith",
    "email": "maria@email.com"
  }
  ```
## Contribution
1. Fork this repository.
2. Create a new branch (`git checkout -b my-feature`).
3. Commit your changes (`git commit -m 'My new feature'`).
4. Push to the remote repository (`git push origin my-feature`).
5. Open a Pull Request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

