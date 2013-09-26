/*Exercice 1*/

create table ETUDIANT
(net number(8) primary key,
nom varchar(15),
age number(2));

insert into etudiant values (01254284,'Kuntz',19);
insert into etudiant (net,nom) values (1,22,'Darksoul');
insert into etudiant (net,nom) values (2,'Demonsoul');

update etudiant
set age=20
where nom='Demonsoul';

delete from etudiant
where nom='Kuntz';

alter table etudiant add constraint CK_majeur check (age>=18);
/*
insert into etudiant values(3,'pokemon',15);
*/

alter table etudiant add adresse varchar(50);

insert into etudiant values (3,'Lighting',23,'Pulse');

/*Exercice 2*/

create table cout
(age number(2) primary key, tarif number(10), constraint ck_tarif  check (tarif in (1,2,3)));

insert into cout values (22,1);
insert into cout values (23,2);
insert into cout values (20,3);
insert into cout (age) values (23);
insert into cout values (24,5);

alter table etudiant add constraint fk_age foreign key (age) references cout (age); 

insert into etudiant values (6,'Starcraft2',25,'USA');
insert into etudiant values (6,'Starcraft2',22,'USA');

delete from cout where age=22;


/*Exercice 3 */

create table inscription 
(net number(8) primary key,
diplome varchar(100),
constraint fk_net foreign key (net) references etudiant (net));

insert into inscription values (3,'Liscence Informatique');

insert into inscription values (8,'BTS Informatique');

delete from etudiant where nom='Lighting';

alter table inscription drop constraint fk_net;
alter table inscription add constraint fk_net foreign key (net) references etudiant (net) on delete cascade;


