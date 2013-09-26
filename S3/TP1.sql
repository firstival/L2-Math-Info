select 1+mod(12,5) from dual;

select sysdate from dual;



select * from reser inner join circuit on circuit.nc=reser.nc;

select distinct nomc from reser order by nomc;

select distinct nc, prix from circuit order by prix;

select vdep,nc from circuit;



select nomc from reser where to_char(datedep,'YYYY')=2005;

select nomc from reser where (to_char(datedep,'YYYY')=2006 and (to_char(datedep,'MM')>=04)) or (to_char(datedep,'YYYY')>2006);

select distinct nomc from reser where (to_char(sysdate,'YYYY') - to_char(datedep,'YYYY'))<=5;




select distinct nomc from reser where to_char(datedep,'MM') in ('05','09');

select distinct nc from circuit
where (vdep not in ('Londres','Amsterdam') and varr not in ('Londres','Amsterdam'))
and (nc not in (select nc from ciretape where vilet not in ('Londres','Amsterdam')));

select nr,nc from reser where to_char(datedep,'MM') between 04 and 09 order by nr;

select nc,datedep,nbres from reser where nomc='Picsou';

select nomv from ville where nomv like '%Port%';