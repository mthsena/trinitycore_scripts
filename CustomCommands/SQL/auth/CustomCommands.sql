
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES 
('1001', 'Command: .chat'),
('1002', 'Command: .buff'),
('1003', 'Command: .shop'),
('1004', 'Command: .mail'),
('1005', 'Command: .bank'),
('1006', 'Command: .maxskills'),
('1007', 'Command: .tele'),
('1008', 'Command: .scale'),
('1009', 'Command: .hover'),
('1010', 'Command: .customize'),
('1011', 'Command: .changerace'),
('1012', 'Command: .changefaction'),
('1013', 'Command: .transfer'),
('1014', 'Command: .castall'),
('1015', 'Command: .summonall');

INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES 
('195', '1001'),
('195', '1002'),
('195', '1003'),
('195', '1004'),
('195', '1005'),
('195', '1006'),
('195', '1007'),
('195', '1008'),
('195', '1009'),
('195', '1010'),
('195', '1011'),
('195', '1012'),
('192', '1013'),
('192', '1014'),
('192', '1015');
