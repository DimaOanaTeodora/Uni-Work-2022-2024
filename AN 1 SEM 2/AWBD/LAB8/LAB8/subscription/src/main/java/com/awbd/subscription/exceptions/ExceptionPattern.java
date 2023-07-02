package com.awbd.subscription.exceptions;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.Date;

@Data
@AllArgsConstructor
public class ExceptionPattern {
    Date date;
    String message;
    String description;
}
