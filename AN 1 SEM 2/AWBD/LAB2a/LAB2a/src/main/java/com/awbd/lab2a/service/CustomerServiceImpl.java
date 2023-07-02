package com.awbd.lab2a.service;

import java.util.ArrayList;
import java.util.List;


import com.awbd.lab2a.configuration.Log;
import com.awbd.lab2a.model.Customer;
import org.springframework.stereotype.Service;



@Service
public class CustomerServiceImpl implements CustomerService {


	@Override
	@Log
	public List<Customer> findAll() {
		List<Customer> customers = new ArrayList<Customer>();
		Customer customer1 = Customer.builder().id(1L).firstName("Andrei").lastName("Popescu")
				.email("ap@unibuc.com").build();

		Customer customer2 = Customer.builder().id(1L).firstName("Maria").lastName("Georgescu")
				.email("mg@unibuc.com").build();

		customers.add(customer1);
		customers.add(customer2);
		return customers;
	}

	@Override
	public Customer save(Customer customer) {
		return null;
	}

}





