package com.awbd.lab2a.configuration;

import lombok.extern.slf4j.Slf4j;
import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

@Component
@Aspect
@Slf4j
public class LoggingAspect {

    @Pointcut("@annotation(Log)")
    public void logAnnotation(){
    }

    @Pointcut("within(com.awbd.lab2a..*)")
    public void logPackage(){

    }

    @Pointcut("execution(public com.awbd.lab2a.model.Customer *.save(..))")
    public void logMethod(){

    }


    @After("logAnnotation()")
    public void logMethodCallAdvice(JoinPoint joinPoint){
        log.info("aspect log after " + joinPoint.getSignature());
    }

    @Before("logPackage()")
    public void logPackageAdvice(JoinPoint joinPoint){
        log.info("aspect log before " + joinPoint.getSignature());
    }

    @After("logMethod()")
    public void logSetterAdvice(JoinPoint joinPoint){
        log.info("aspect log after " + joinPoint.getSignature());
        log.info("aspect log param " + joinPoint.getArgs()[0]);
    }
}