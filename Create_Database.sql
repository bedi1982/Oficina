--/*Create the database manually:
--V2:

create Database Oficina;
use Oficina;

CREATE TABLE Client (
        Client_id bigint PRIMARY KEY AUTO_INCREMENT,
        Client_Name varchar(40),
        Client_Address varchar(50),
        Client_City varchar(30),
        Client_CPG varchar(20),
        Client_ID_Number varchar(15),
        Client_Phone varchar(40),
        Client_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        Client_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Employee (
        Employee_id bigint PRIMARY KEY AUTO_INCREMENT,
        Employee_Name varchar(40),
        Employee_Address varchar(50),
        Employee_City varchar(30),
        Employee_CPG varchar(20),
        Employee_ID_Number varchar(15),
        Employee_Phone varchar(40),
        Employee_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        Employee_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        Employee_Password varchar(40)
);

CREATE TABLE Part (
        Part_id bigint PRIMARY KEY AUTO_INCREMENT,
        Part_Name varchar(50),
        Part_Description varchar(250),
        Part_Cost Double(19,2),
        Part_Sell_Price Double(19,2),
        Part_Quantity int,
        Part_Active boolean not null default 1,
        Part_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        Part_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Service(
        Service_id bigint PRIMARY KEY AUTO_INCREMENT,
        Service_Client_id bigint,
        Service_Client_Carid bigint,
        Service_Short_Description varchar(70),
        Service_Finished boolean not null default 0,
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
        ClientCar_Plate varchar(10),
        ClientCar_Color varchar(26),
        ClientCar_updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
        ClientCar_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE HourCost(
        HourCost_id bigint PRIMARY KEY AUTO_INCREMENT,
        HourCost Double not null default 0,
        Hour_Cost_created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

--Initialize
INSERT INTO HourCost (HourCost) values (0);
INSERT INTO Employee (Employee_Name, Employee_Password) values ("root", "root");

--sql tips:
--Changing column name:
--ALTER TABLE Service CHANGE `finished` Service_Finished boolean not null default 0;
