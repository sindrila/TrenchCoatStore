# Trench Coat Store 🧥
A C++ app for managing and shopping trench coats using Qt GUI framework.

<img width="620" alt="Screenshot 2024-01-28 at 18 26 14" src="https://github.com/sindrila/TrenchCoatStore/assets/115073810/9d676c61-dd07-44cf-bc55-6a1a40ce4868">

This app has two modes: administrator and user. 

# Administrator mode

The administrator can add, remove, or update trench coats from the inventory using a graphical interface. 

<img width="1973" alt="image" src="https://github.com/sindrila/TrenchCoatStore/assets/115073810/d170523f-3eaf-4ec0-859a-57646287f5f9">


# User mode
The user can browse, and buy trench coats from the available stock. The user can also export their shopping cart to an HTML or CSV file. 

<img width="1252" alt="Screenshot 2024-01-28 at 18 27 35" src="https://github.com/sindrila/TrenchCoatStore/assets/115073810/0b215203-04d1-4824-bc1d-1ddf88915553">


# Technical details

The app follows a layered architecture with four main components: GUI, Service, Repository, and Domain:
- **GUI layer** is responsible for the user interface and interaction using Qt framework. To fetch and display the images of trench coats, it uses curl and opencv libraries.
- **Service layer** provides the business logic and functionality of the app, such as adding, updating, or removing trench coats.
- **Repository layer** handles the available trench coat entities, as well as the user shopping cart.
- **Domain layer** defines the entities and models of the app, such as TrenchCoat
  
