package com.awbd.discount;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.context.config.annotation.RefreshScope;

@SpringBootApplication
@RefreshScope
public class DiscountApplication {

	public static void main(String[] args) {
		SpringApplication.run(DiscountApplication.class, args);
	}

}
