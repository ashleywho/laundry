-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 22, 2022 at 07:07 PM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 7.3.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `laundry`
--

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `customerId` int(11) NOT NULL,
  `customerName` varchar(50) NOT NULL,
  `customerPassword` varchar(16) NOT NULL,
  `customerPhone` varchar(10) NOT NULL,
  `customerEmail` varchar(50) NOT NULL,
  `pickUpDate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`customerId`, `customerName`, `customerPassword`, `customerPhone`, `customerEmail`, `pickUpDate`) VALUES
(54, 'Syakira', 'syakira', '0102529566', 'syakira@gmail.com', '0000-00-00');

-- --------------------------------------------------------

--
-- Table structure for table `ordering`
--

CREATE TABLE `ordering` (
  `orderId` int(10) NOT NULL,
  `customerID` int(11) NOT NULL,
  `serviceId` int(10) NOT NULL,
  `list` varchar(25) NOT NULL,
  `quantity` int(10) NOT NULL,
  `amount` int(10) NOT NULL,
  `status` varchar(25) NOT NULL,
  `pickUpStatus` varchar(25) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `ordering`
--

INSERT INTO `ordering` (`orderId`, `customerID`, `serviceId`, `list`, `quantity`, `amount`, `status`, `pickUpStatus`) VALUES
(198, 54, 8, 'Dress', 3, 22, 'Paid and Processing', 'Completed');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `cartId` int(10) NOT NULL,
  `serviceId` int(10) NOT NULL,
  `customerId` int(11) NOT NULL,
  `itemQuantity` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `service`
--

CREATE TABLE `service` (
  `serviceId` int(10) NOT NULL,
  `name` varchar(25) NOT NULL,
  `description` varchar(500) NOT NULL,
  `price` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `service`
--

INSERT INTO `service` (`serviceId`, `name`, `description`, `price`) VALUES
(1, 'Baju Kebaya', 'Baju Kebaya', 28),
(2, 'Baju Kurung', 'Baju Kurung', 28),
(3, 'Baju Melayu', 'Baju Melayu', 28),
(4, 'Blouse', 'Blouse', 14),
(5, 'Bridal Gown', 'Bridal Gown', 227),
(6, 'Cap', 'Cap', 15),
(7, 'Cardigan', 'Cardigan', 22),
(8, 'Dress', 'Dress', 22),
(9, 'Glove', 'Gloves', 11),
(10, 'Jacket', 'Jacket', 27),
(11, 'Jersey', 'Jersey', 15),
(12, 'Winter Boots', 'Winter Boots', 50),
(19, 'Bed Sheets', 'Bed Sheets', 35),
(20, 'Polo T', 'Shirts', 26),
(21, 'Jeans', 'Jeans', 30);

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `staffId` int(11) NOT NULL,
  `staffUName` varchar(20) NOT NULL,
  `staffPassword` varchar(20) NOT NULL,
  `staffEmail` varchar(25) NOT NULL,
  `staffPhone` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`staffId`, `staffUName`, `staffPassword`, `staffEmail`, `staffPhone`) VALUES
(1, 'Syakira Nadila', 'syakira', 'syanadila@gmail.com', '0138835744'),
(2, 'Aliff Najmi', 'aliff', 'aliffjemi@gmail.com', '0123456789');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`customerId`);

--
-- Indexes for table `ordering`
--
ALTER TABLE `ordering`
  ADD PRIMARY KEY (`orderId`),
  ADD KEY `serviceFK` (`serviceId`),
  ADD KEY `customerFK` (`customerID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`cartId`);

--
-- Indexes for table `service`
--
ALTER TABLE `service`
  ADD PRIMARY KEY (`serviceId`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`staffId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `customerId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=55;

--
-- AUTO_INCREMENT for table `ordering`
--
ALTER TABLE `ordering`
  MODIFY `orderId` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=199;

--
-- AUTO_INCREMENT for table `payment`
--
ALTER TABLE `payment`
  MODIFY `cartId` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=120;

--
-- AUTO_INCREMENT for table `service`
--
ALTER TABLE `service`
  MODIFY `serviceId` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;

--
-- AUTO_INCREMENT for table `staff`
--
ALTER TABLE `staff`
  MODIFY `staffId` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `ordering`
--
ALTER TABLE `ordering`
  ADD CONSTRAINT `customerFK` FOREIGN KEY (`customerID`) REFERENCES `customer` (`customerId`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `serviceFK` FOREIGN KEY (`serviceId`) REFERENCES `service` (`serviceId`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
