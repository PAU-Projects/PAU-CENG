use myTestDB
go
alter trigger update_t2 on t1
for update
as
begin
 set nocount on
 
 update t2
 set t2_value = i.t1_value
 from inserted as i
 inner join t2 on t2.id = i.id
 
end
go
update t1
set t1_value = cast(id as varchar(50))
go