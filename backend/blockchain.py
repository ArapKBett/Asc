from web3 import Web3
import json

class Blockchain:
    def __init__(self):
        # Connect to Ganache (replace with Render URL post-deployment)
        self.w3 = Web3(Web3.HTTPProvider('http://127.0.0.1:7545'))
        self.account = self.w3.eth.accounts[0]
        
        # Load deployed contract
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
        signed_tx = self.w3.eth.account.signTransaction(tx, private_key='YOUR_GANACHE_PRIVATE_KEY')
        tx_hash = self.w3.eth.sendRawTransaction(signed_tx.rawTransaction)
        return self.w3.toHex(tx_hash)

    def verify_evidence(self, file_hash):
        return self.contract.functions.verifyEvidence(file_hash).call()
