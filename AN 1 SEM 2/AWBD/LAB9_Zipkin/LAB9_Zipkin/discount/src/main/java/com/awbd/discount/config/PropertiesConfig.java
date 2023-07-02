package com.awbd.discount.config;

import lombok.Getter;
import lombok.Setter;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Component
@ConfigurationProperties("percentage")
@Getter
@Setter
public class PropertiesConfig {
    private int month;
    private int year;
}
