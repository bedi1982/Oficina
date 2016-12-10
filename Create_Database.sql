--/*Create the database manually:
--V2:

create Database Oficina;
use Oficina;

CREATE TABLE Client (
        Client_id bigint PRIMARY KEY AUTO_INCREMENT,
        Client_Name varchar(40),
        Client_Address varchar(50),
        Client_City varchar(30),
        Client_CPF varchar(20),
        Client_RG varchar(15),
        Client_Phone varchar(40),
        Client_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        Client_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Part (
        Part_id bigint PRIMARY KEY AUTO_INCREMENT,
        Part_Name varchar(50),
        Part_Description varchar(250),
        Part_Cost Double(19,2),
        Part_Quantity int,
        Part_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        Part_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Service(
        Service_id bigint PRIMARY KEY AUTO_INCREMENT,
        Service_Client_id bigint,
        Service_Client_Carid bigint,
        Service_Short_Description varchar(70),
        Service_Description varchar(1000),
        Service_Parts_Cost Double(19,2),
        Service_Hours_Duration Double(19,2),
        Service_Hour_Cost Double(19,2),
        Service_Paid boolean not null default 0,
        Service_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        Service_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE ServicePartsUsed(
        ServicePartsUsed_id bigint PRIMARY KEY AUTO_INCREMENT,
        Used_On_What_Service_id bigint,
        Used_Part_ID bigint
);

CREATE TABLE ClientCar(
        ClientCar_id bigint PRIMARY KEY AUTO_INCREMENT,
        ClientCar_Client_id bigint,
        ClientCar_Model varchar(50),
        ClientCar_Description varchar(300),
        ClientCar_BuiltYear int,
        ClientCar_Placa varchar(10),
        ClientCar_Color varchar(26),
        ClientCar_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        ClientCar_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE HourCost(
        HourCost_id bigint PRIMARY KEY AUTO_INCREMENT,
        HourCost Double,
        HourCost_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

insert into HourCost (HourCost) values (0);
