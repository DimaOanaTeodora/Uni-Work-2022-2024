delete from product_category;
delete from product;
delete from category;
delete from participant;

insert into category(id, name) values(1, 'paintings');
insert into category(id, name) values(2, 'sculptures');
insert into category(name) values('books');

insert into participant(id, last_name, first_name) values(1, 'Adam', 'George');

insert into product (id, name, code, reserve_price, restored, seller_id) values (1, 'The Card Players', 'PCEZ', 250, 0, 1);

insert into product_category values(1,1);

