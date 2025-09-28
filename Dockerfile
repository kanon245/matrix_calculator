FROM ubuntu:22.04 AS builder
RUN apt-get update && \
 apt-get install -y cmake g++ git && \
 rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN rm -rf build && \
 cmake -B build && \
 cmake --build build --target matrix_calculator
FROM ubuntu:22.04
WORKDIR /app
COPY --from=builder /app/build/matrix_calculator .
CMD ["./matrix_calculator"]
