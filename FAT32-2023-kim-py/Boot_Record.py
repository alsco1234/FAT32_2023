if __name__ == '__main__':
    with open('../FAT32_simple.mdf', mode='rb') as file:
        binaryData = file.read(16)
        binaryDataString = [x for x in binaryData]
        print(binaryDataString)