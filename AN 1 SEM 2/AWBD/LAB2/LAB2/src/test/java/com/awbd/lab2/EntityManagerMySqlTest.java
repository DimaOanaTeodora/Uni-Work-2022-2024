package com.awbd.lab2;

import com.awbd.lab2.domain.Currency;
import com.awbd.lab2.domain.Product;
import jakarta.persistence.EntityManager;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.test.annotation.Rollback;
import org.springframework.test.context.ActiveProfiles;

import static org.junit.jupiter.api.Assertions.assertEquals;


@DataJpaTest
@ActiveProfiles("mysql")
@AutoConfigureTestDatabase(replace = AutoConfigureTestDatabase.Replace.NONE)
@Rollback(false)
public class EntityManagerMySqlTest {

    @Autowired
    private EntityManager entityManager;

    @Test
    public void findProduct() {

        Product productFound = entityManager.find(Product.class, 1L);

        assertEquals(productFound.getCode(), "PCEZ");
    }

    @Test
    public void updateProduct() {

        Product productFound = entityManager.find(Product.class, 1L);
        productFound.setCurrency(Currency.EUR);

        entityManager.persist(productFound);

        productFound = entityManager.find(Product.class, 1L);
        assertEquals(Currency.EUR, productFound.getCurrency());

        entityManager.flush();

    }

}
