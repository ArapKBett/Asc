// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract EvidenceChain {
    struct Evidence {
        string fileHash;
        string filename;
        uint timestamp;
    }

    mapping(string => Evidence) public evidenceRecords;

    event EvidenceStored(string fileHash, string filename, uint timestamp);

    function storeEvidence(string memory fileHash, string memory filename) public {
        evidenceRecords[fileHash] = Evidence(fileHash, filename, block.timestamp);
        emit EvidenceStored(fileHash, filename, block.timestamp);
    }

    function verifyEvidence(string memory fileHash) public view returns (bool) {
        return keccak256(abi.encodePacked(evidenceRecords[fileHash].fileHash)) == keccak256(abi.encodePacked(fileHash));
    }
}