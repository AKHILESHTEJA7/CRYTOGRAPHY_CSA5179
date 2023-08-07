import hashlib

def calculate_md5(input_string):
    md5_hash = hashlib.md5()
    md5_hash.update(input_string.encode('utf-8'))
    return md5_hash.hexdigest()

if __name__ == "__main__":
    input_string = "Hello, world!"
    md5_result = calculate_md5(input_string)
    print("MD5 hash of input string:", md5_result)
