package com.awbd.subscription.model;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
@AllArgsConstructor
public class Discount {
    private int month;
    private int year;
    private String versionId;
}
