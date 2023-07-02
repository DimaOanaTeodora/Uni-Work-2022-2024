package com.awbd.lab6;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;

@SpringBootApplication(exclude = {DataSourceAutoConfiguration.class })
public class Lab6Application {

	public static void main(String[] args) {
		SpringApplication.run(Lab6Application.class, args);
	}

}
