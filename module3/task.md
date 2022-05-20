# Shared memory
Для закрепления полученных знаний напишите две программы, осуществляющие взаимодействие через разделяемую память. Первая программа должна создавать сегмент разделяемой памяти и копировать туда свой собственный исходный текст, вторая программа должна брать оттуда этот текст, печатать его на экране и удалять сегмент разделяемой памяти из системы.
# Semaphore
Модифицируйте программы /ftp/pub/sem6-7/stud/06-3a.c и /ftp/pub/sem6-7/stud/06-3b.c, которые иллюстрировали некорректную работу через разделяемую память, обеспечив с помощью семафоров взаимоисключения для их правильной работы. 
# Multiplex
Напишите, откомпилируйте и прогоните программы сервера и клиентов для предложенной схемы мультиплексирования сообщений. 
# Socket
По аналогии с программами в предыдущем примере модифицируйте тексты программ TCP клиента и сервера для сервиса echo (программа 15–16-3.c и программа 15–16-4.c ) для потокового общения в семействе UNIX Domain протоколов. Откомпилируйте их и убедитесь в правильном функционировании.