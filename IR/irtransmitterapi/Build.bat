dotnet publish IrTransmitterApi.sln --configuration Release
docker image build -f Dockerfile.rp -t 192.168.1.125:5000/irtransmitterapi .
docker push 192.168.1.125:5000/irtransmitterapi