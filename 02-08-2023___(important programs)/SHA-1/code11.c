import hashlib

def calculate_sha1(input_string):
    sha1_hash = hashlib.sha1()
    sha1_hash.update(input_string.encode('utf-8'))
    return sha1_hash.hexdigest()

if __name__ == "__main__":
    input_string = "Hello, world!"
    sha1_result = calculate_sha1(input_string)
    print("SHA-1 hash of input string:", sha1_result)
