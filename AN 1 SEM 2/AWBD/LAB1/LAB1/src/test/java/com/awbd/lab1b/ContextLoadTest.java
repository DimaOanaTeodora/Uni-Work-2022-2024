package com.awbd.lab1b;
import org.junit.Test;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class ContextLoadTest {
    @Test
    public void contructorDI(){
        ClassPathXmlApplicationContext context =
                new ClassPathXmlApplicationContext("applicationContextCS.xml");

        Subscription myBooksSubscription= context.getBean("myBooksSubscription", Subscription.class);

        System.out.println(myBooksSubscription.getPrice() + " " + myBooksSubscription.getDescription());

        context.close();
    }
    @Test
    public void setterDI(){
        ClassPathXmlApplicationContext context =
                new ClassPathXmlApplicationContext("applicationContextCS.xml");

        Subscription myMoviesSubscription = context.getBean("myMoviesSubscription", Subscription.class);

        System.out.println(myMoviesSubscription.getPrice() + " " + myMoviesSubscription.getDescription());

        context.close();
    }


    @Test
    public void propertyDITest(){
        ClassPathXmlApplicationContext context =
                new ClassPathXmlApplicationContext("applicationContextCS.xml");
        Subscription mySportSubscription = context.getBean("mySportSubscription", Subscription.class);
        System.out.println(mySportSubscription.getPrice() + " "
                + mySportSubscription.getDescription());
        context.close();
    }

}
