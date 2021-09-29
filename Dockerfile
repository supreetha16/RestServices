FROM amytabb/docker_ubuntu16_essentials
ENV LD_LIBRARY_PATH /usr/local/lib
WORKDIR /CodeBase/
RUN git clone https://github.com/civetweb/civetweb.git
RUN git clone https://github.com/supreetha16/RestServices.git
RUN cd civetweb;make slib 
RUN cd civetweb;make install-slib
RUN cd RestServices;gcc -o myprog CivetWeb_Example2.cpp -I /CodeBase/civetweb/include -L/CodeBase/civetweb/ -lcivetweb
EXPOSE 8888
CMD ["RestServices/myprog"] 
