# Step_base
select name, birthday, post_or_faculty
from table_person, table_result, table_staff
where table_result.id_person = table_person.id
and table_result.id_work = table_staff.id
and name = 'Shrek'
order by name;


C:\\Users\\VLAD\\Documents\\Step_base\\Step_base.sqlite


C:\\Users\\VLAD\\Documents\\Step_base\\Step_base.csv