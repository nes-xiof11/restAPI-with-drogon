
# **REST API with C++ and Drogon**  

This repository contains the implementation of a REST API using the Drogon framework in C++. The architecture is inspired by one that we are using in my work, and I really liked its structure.  

## **Technologies Used**  
- **C++**  
- **Drogon** (web framework in C++)  
- **XMake** (for build management)  
- **sqlite_orm** (ORM for SQLite)  

## **Requirements**  
Before starting, ensure you have installed:  
- **C++17 or later**  
- **XMake**  
- **Drogon**  

## **Installation and Setup**  
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

## **Available Endpoints**  
The API exposes the following endpoints:  

### **GET /**  
- **Description:** Default endpoint for status check.  
- **Response:**  
  ```json
  {
    "message": "API online"
  }
  ```

### **GET /api/v1/user/list/**  
- **Description:** Returns a list of registered users.  
- **Response:**  
  ```json
  [
    {
      "id": 2,
      "name": "Cebola",
      "nickname": "Cebola",
      "email": "cebola@gmail.com",
      "password": "----",
      "created_at": "2025-03-16 13:58"
    }
  ]
  ```

### **POST /api/v1/user/**  
- **Description:** Registers a new user.  
- **Request:**  
  ```json
  {
    "name": "Cebola",
    "nickname": "Cebola",
    "email": "cebola@gmail.com",
    "password": "----"
  }
  ```
- **Response:**  
  ```json
  {
    "id": 2,
    "name": "Cebola",
    "nickname": "Cebola",
    "email": "cebola@gmail.com",
    "password": "----",
    "created_at": "2025-03-16 13:58"
  }
  ```

## **Contribution**  
1. Fork this repository.  
2. Create a new branch (`git checkout -b your-feature`).  
3. Commit your changes (`git commit -m 'Your feature'`).  
4. Push to the remote repository (`git push origin your-feature`).  
5. Open a Pull Request.  

## **License**  
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.  