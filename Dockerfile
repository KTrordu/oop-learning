# Ubuntu tabanlı C++ geliştirme ortamı
FROM ubuntu:22.04

# Sistem güncellemesi ve gerekli paketleri yükle
RUN apt-get update && apt-get install -y \
    g++ \
    gcc \
    make \
    cmake \
    gdb \
    valgrind \
    vim \
    nano \
    git \
    && rm -rf /var/lib/apt/lists/*

# Çalışma dizini oluştur
WORKDIR /workspace

# Varsayılan komut
CMD ["/bin/bash"]