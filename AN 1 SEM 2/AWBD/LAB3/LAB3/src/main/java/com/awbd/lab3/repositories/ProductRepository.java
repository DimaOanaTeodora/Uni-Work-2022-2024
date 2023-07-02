package com.awbd.lab3.repositories;

import com.awbd.lab3.domain.Product;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface ProductRepository extends PagingAndSortingRepository<Product, Long> {
    @Query("select p from Product p where p.seller.id = ?1")
    List<Product> findBySeller(Long sellerId);

    @Query("select p from Product p where p.seller.firstName = :firstName and p.seller.lastName = :lastName")
    List<Product> findBySellerName(@Param("firstName") String sellerFirstName, @Param("lastName") String sellerLastName);

}
