\mysql\bin\mysqladmin refresh
perl run-all-tests --log --comment "2x Pentium II 400mz, 256M, under vmware"
del limits\mysql-org.cfg
move limits\mysql.cfg limits\mysql-org.cfg
perl crash-me --force
