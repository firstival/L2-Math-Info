select vilet from ciretape where nc in (select nc from reser where nomc='GrosseBaf');

select distinct nc from ciretape where vilet in (select nomv from ville where pays='Irlande');

/* ici*/
select nomv from monument group by nomv having (count(nomm))>1

select nc,vdep,varr from circuit where nc in (select distinct nc from cirprog where
((to_char(datedep, 'DD')>17 and to_char(datedep, 'MM')=04 and to_char(datedep, 'YYYY')=2006)
or (to_char(datedep, 'MM')>04 and to_char(datedep, 'YYYY')=2006)
or (to_char(datedep, 'YYYY')>2006))
and nblibr>10);

select nomm from monument where nomv in (select vilet from ciretape where nc in (select nc from reser where nomc='Asterix'));

select nc,vdep from circuit where nc in (select nc from ciretape where vilet in (select nomv from ville where pays='Angleterre'));

select circuit.nc,reser.nomc from circuit,reser where circuit.nc=reser.nc(+);





select count(nomm)"Nombre de monument" from monument where nomv in (select nomv from ville where pays='France');

select avg(prix)"prix moyen" from circuit;

select nomc,sum(nbres)"nombre de réservation" from reser group by nomc;

select nc,prix from circuit where prix=(select max(prix) from circuit);

select nomv from monument group by nomv having count(nomm)>1;

select count(nomm) from monument where nomv in (select vilet from ciretape where nc in (select nc from reser where nomc='Donald'));

select nomv, count(nomm)"Nombre de monument par ville" from monument where nomv in (select vilet from ciretape where nc in (select nc from reser where nomc='Donald')) group by nomv;

select nomc,sum(nbres * prix)"Facture totale" from reser,circuit where reser.nc=circuit.nc group by nomc;

select max(sum(nbres * prix))"Facture la plus grosse" from reser,circuit where reser.nc=circuit.nc group by nomc;

select nomc from reser,circuit where reser.nc=circuit.nc group by nomc having sum(nbres * prix) in (select max(sum(nbres * prix)) from reser,circuit where reser.nc=circuit.nc group by nomc);

select count(nomm) from monument where nomv in (select vilet from ciretape where nc in (select nc from reser where nomc='Donald'));

SELECT nomc, count(m.nomm) AS monuments_vus FROM reser r
INNER JOIN ciretape c ON r.nc = c.nc
INNER JOIN monument m ON c.vilet = m.nomv
GROUP BY nomc;
