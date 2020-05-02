# Parameter för unique_users:
# uniq-fil, start_period, end_period, butiker ...

select unique_users("mmkonto_butik",1,12,"250600") from mm_system ;

select unique_users("mmkonto_butik",1,12,"250700","250600","250800") from mm_system ;

select unique_users("mmkonto_butik",1,24,"250700","250600","250800") from mm_system ;

select butik,unique_users("mmkonto_butik",1,1,butik) from butik where butik >= 250500 and butik <= 250800;

# Parameter för group_unique_users:
# uniq-fil, start_period, end_period, butik

select butik,group_unique_users("mmkonto_butik",1,12,butik) from butik where butik >= 250500 and butik <= 250800 group by butik;

select group_unique_users("mmkonto_butik",1,12,butik) from butik where butik >= 250500 and butik <= 250800 ;
