from web3 import Web3
import json
import os

class Blockchain:
    def __init__(self):
        # Use Infura Sepolia testnet URL with your Project ID
        self.w3 = Web3(Web3.HTTPProvider('https://sepolia.infura.io/v3/YOUR_INFURA_PROJECT_ID'))
        # Replace with your Ethereum account address (e.g., from MetaMask)
        self.account = 'YOUR_PUBLIC_ADDRESS'
        
        with open('../contracts/EvidenceChain.json', 'r') as f:
            contract_data = json.load(f)
        self.contract = self.w3.eth.contract(
            address=contract_data['address'],
            abi=contract_data['abi']
        )

    def store_evidence(self, file_hash, filename):
        tx = self.contract.functions.storeEvidence(file_hash, filename).buildTransaction({
            'from': self.account,
            'nonce': self.w3.eth.getTransactionCount(self.account),
            'gas': 2000000,
            'gasPrice': self.w3.toWei('20', 'gwei')
        })
        # Use environment variable for private key
        signed_tx = self.w3.eth.account.signTransaction(tx, private_key=os.getenv('YOUR_GANACHE_PRIVATE_KEY'))
        tx_hash = self.w3.eth.sendRawTransaction(signed_tx.rawTransaction)
        return self.w3.toHex(tx_hash)

    def verify_evidence(self, file_hash):
        return self.contract.functions.verifyEvidence(file_hash).call()
