package com.awbd.lab2a.service;



import com.awbd.lab2a.model.Customer;

import java.util.List;

public interface CustomerService {

	public List<Customer> findAll();
	public Customer save(Customer customer);

	
}
