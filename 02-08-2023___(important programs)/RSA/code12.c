from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

def generate_key_pair():
    key = RSA.generate(2048)  # 2048-bit key size (adjust as needed)
    private_key = key.export_key()
    public_key = key.publickey().export_key()
    return private_key, public_key

def encrypt_data(public_key, data):
    rsa_key = RSA.import_key(public_key)
    cipher = PKCS1_OAEP.new(rsa_key)
    encrypted_data = cipher.encrypt(data.encode('utf-8'))
    return encrypted_data

def decrypt_data(private_key, encrypted_data):
    rsa_key = RSA.import_key(private_key)
    cipher = PKCS1_OAEP.new(rsa_key)
    decrypted_data = cipher.decrypt(encrypted_data)
    return decrypted_data.decode('utf-8')

if __name__ == "__main__":
    
    private_key, public_key = generate_key_pair()

    plaintext = "This is a secret message."

    encrypted_data = encrypt_data(public_key, plaintext)
    print(f"Encrypted data: {encrypted_data.hex()}")

    decrypted_data = decrypt_data(private_key, encrypted_data)
    print(f"Decrypted data: {decrypted_data}")
